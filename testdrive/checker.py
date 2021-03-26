import sys
import os
import filecmp
import subprocess

TGREY = '\033[30m'  # Grey Text
TRED =  '\033[31m' # Red Text
TGREEN =  '\033[32m' # Green Text
TYELLOW =  '\033[33m' # Yellow Text
TCYAN = '\033[36m' # Cyan Text
BPURPLE = '\033[44m' # Purple Background
BYELLOW = '\033[43m' # Yellow Background
BGREEN = '\033[42m' # GREEN Background
BLIGTH_BLUE = '\033[104m' # BLUE Background
TMAGENTA = '\033[35m'
BRED = '\033[41m' # RED Background
ENDC = '\033[m' # reset to the defaults

UP_LINE = '\033[A'
ERASE_LINE = '\033[2K'
BOLD = '\033[1m'

SUCCESS = 0
BOTH_MISSING = 1
BEHAVIORS_DIFFERS = 2
FAILED = 3

os.system('clear')
args = sys.argv
files = []
mode = ""
src_mode = False
src_folder = "f "
oneline_mode = False
leaks_mode = False

def check_args(args):
	print("\n\n")
	print(src_folder)
	for arg in enumerate(args):
		print("current arg :", arg[1])
		if arg[1] == "-f":
			try:
				if os.path.isdir(args[arg[0] + 1]):
					src_mode = True
					src_folder = args[arg[0] + 1]
				else:
					print("Wrong path")
			except:
				print("Not valid folder path")
	print("folder : ", src_folder)

if (len(args) > 1 and args[1] == "--oneline"):
	args.pop(1)
	mode = "--oneline"

if (len(args) > 1 and "--leaks" in args):
	leaks_mode = True

if len(args) > 1 and "-f" in args:
	for arg in args:
		if arg[-2:] == ".s":
			files = [arg]
			break
else:
	files = os.listdir('./src')

path_asm_own = './asm_own'
path_asm_model = './asm_model'
out_own_path = 'output/own/'
out_model_path = 'output/model/'

class Test:
	def __init__(self, file, path_asm_own, path_asm_model, out_own_path, out_model_path):
		self.file = file
		self.cor_file = file[:-1] + 'cor'
		self.src_cor_file = 'src/' + self.cor_file
		self.path_asm_own = path_asm_own
		self.path_asm_model = path_asm_model
		self.out_own_path = out_own_path
		self.out_model_path = out_model_path
		self.result = -1
		self.file_missing = 0

	def run_test(self):
		if (mode == ""):
			print(BPURPLE + TGREY + '<===== Test Source file : ' + ENDC + BPURPLE + self.file + ENDC + BPURPLE + TGREY + ' =====>' + ENDC)
		elif (mode == "--oneline"):
			print(BOLD + TCYAN + "Testing\t\t"  + self.file.ljust(40, ' ') + ENDC + '\t', end = '')
		self.run_bins()
		if self.file_missing == 0:
			self.cmp_outputs()

	def run_bins(self):
		self.__check_or_create_folders()
		self.__debug_print('\tCompiling with YOUR asm ...')
		os.system(self.path_asm_own + ' src/' + self.file + ' > /dev/null')
		if leaks_mode:
			subprocess.run(["/usr/bin/valgrind", "--log-file=" + "output/own/" + self.file[:-2] + ".log", self.path_asm_own , str("src/" + self.file)], stdout=subprocess.PIPE).stdout
		if os.path.isfile('src/' + self.cor_file):
			self.__debug_print('\town .cor is here')
			os.system('mv ' + self.src_cor_file + ' '+ self.out_own_path)
		else:
			self.file_missing += 1
			self.__debug_print('\t' + TYELLOW + 'No OUTPUTS for your ASM buddy' + ENDC + '\n')
		self.__debug_print('\n\tCompiling with 42 asm ...')
		if mode == "":
			cmd = path_asm_model + ' src/' + self.file
		elif mode == "--oneline":
			cmd = path_asm_model + ' src/' + self.file + ' > /dev/null'
		os.system(cmd)
		if os.path.isfile('src/' + '/' + self.cor_file):
			self.__debug_print(UP_LINE + ERASE_LINE)
			self.__debug_print('\t' + UP_LINE + 'model .cor is here\n')
			os.system('mv ' + self.src_cor_file + ' '+ self.out_model_path)
		else:
			self.file_missing += 2
			self.__debug_print('\t' + TYELLOW + 'No OUTPUTS for 42 ASM' + ENDC + '\n')
		if self.file_missing == 3:
			self.__debug_print('\t' + BGREEN + TGREY + '<===== BOTH MISSING =====>' + ENDC + '\n')
			self.__one_line_print('\t' + BOLD + TGREEN + '[SUCCESS]'.ljust(12, ' ') + ENDC + TGREEN + '(both missing)' + ENDC)
			self.result = 1
		elif self.file_missing != 0 and self.file_missing != 3:
			self.__debug_print('\t' + BYELLOW + TGREY + '<===== BEHAVIORS DIFFERS =====>' + ENDC + '\n')
			self.__one_line_print('\t' + BOLD + TRED + '[FAIL]'.ljust(12, ' ') + ENDC + TYELLOW + '(behavior differ)' + ENDC)
			self.result = 2
		
	def cmp_outputs(self):
		diff = filecmp.cmp(self.out_own_path + self.cor_file, self.out_model_path + self.cor_file)
		if diff is True:
			self.__debug_print('\t' + BGREEN + TGREY + '<===== SUCCESS =====>' + ENDC + '\n')
			self.__one_line_print('\t' + BOLD + TGREEN + '[SUCCESS]'.ljust(12, ' ') + ENDC + TGREEN + '(output match)' + ENDC)
			self.result = 0
		else:
			self.__debug_print('\t' + BRED + TGREY + '<===== FAIL =====>' + ENDC + '\n')
			self.__one_line_print('\t' + BOLD + TRED + '[FAIL]'.ljust(12, ' ') + ENDC + TRED + '(output dont match)' + ENDC)
			self.result = 3
			hexa_own = subprocess.check_output('xxd ' + self.out_own_path + self.cor_file, shell=True, universal_newlines=True)
			hexa_model = subprocess.check_output('xxd ' + self.out_model_path + self.cor_file, shell=True, universal_newlines=True)
			hexa_own_lst = list(hexa_own.split('\n'))
			hexa_model_lst = list(hexa_model.split('\n'))
			line_nb = min(len(hexa_model_lst), len(hexa_own_lst))
			i = 0
			while i < line_nb:
				if hexa_own_lst[i] != hexa_model_lst[i]:
					self.__debug_print("Own   :" + hexa_own_lst[i])
					self.__debug_print("Model :" + hexa_model_lst[i])
					self.__debug_print ("Diff at line " + str(i + 1) + " (" + hexa_own_lst[i][:9] + ")" + '\n')
					break
				i = i + 1

	def __check_or_create_folders(self):
		if os.path.isdir("./output") is False:
			os.system("mkdir output")
		if os.path.isdir("./output/own") is False:
			os.system("mkdir output/own")
		if os.path.isdir("./output/model") is False:
			os.system("mkdir output/model")

	def __debug_print(self, string):
		if mode == "":
			print(string)

	def __one_line_print(self, string):
		if mode == "--oneline":
			print(string)

	def get_result(self):
		return self.result

	def clean_outputs(self):
		cmd = 'rm ' + self.out_own_path + '*' + '&&' + 'rm ' + self.out_model_path + '*'
		os.system(cmd)
	

class Run_Test:	
	def __init__(self, lst_files):
		self.files = lst_files
		self.lst_tests = []
		self.files_nb = len(lst_files)
		self.successes = 0
		self.both_missing = 0
		self.behaviors_diff = 0
		self.failed = 0
	
	def run(self):
		self.create_lst_tests()
		self.run_tests()
		self.count_results()
		self.print_results()

	def create_lst_tests(self):
		for file in self.files:
			self.tmp_test = Test(file, path_asm_own, path_asm_model, out_own_path, out_model_path)
			self.lst_tests.append(self.tmp_test)

	def run_tests(self):
		for test in self.lst_tests:
			test.run_test()

	def count_results(self):
		current_res = 0
		for test in self.lst_tests:
			current_res = test.get_result()
			if current_res is SUCCESS:
				self.successes += 1
			if current_res is BOTH_MISSING:
				self.both_missing += 1
			if current_res is BEHAVIORS_DIFFERS:
				self.behaviors_diff += 1
			if current_res is FAILED:
				self.failed += 1
	
	def print_results(self):
		print("\n" + BLIGTH_BLUE + TGREY + '<===== SUMMARY =====>' + ENDC + '\n')
		print(f"Number of files : {self.files_nb}")
		print(f"===== {TGREEN} Success : {self.successes + self.both_missing} {ENDC}=====")
		print(f"|   Output match : {self.successes} |")
		print(f"|   Both missing : {self.both_missing} |")
		# print(f"|_____________________|")
		print(f" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾")
		print(f"==== {TYELLOW} Behaviors differs : {self.behaviors_diff} {ENDC}====")
		print(f"\n==== {TRED} Failed : {self.failed} {ENDC}====")
	

tests = Run_Test(files)
tests.run()
if leaks_mode:
	os.system("cat output/own/*.log > checker.log")
# check_args(args)