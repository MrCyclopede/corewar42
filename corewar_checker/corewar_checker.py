import sys
import os
import filecmp
import subprocess
import random
import logging


TRED =  '\033[31m' # Red Text
TGREEN =  '\033[32m' # Green 
ENDC = '\033[m' # reset to the defaults

args = sys.argv
# print(f"{self.files}")


class Segfault:
	def __init__(self, nb_test):
		self.files = os.listdir('./src')
		self.nb_test = int(nb_test)
		logging.basicConfig(filename='suspect_cases.log',level=logging.DEBUG)

	def	check_output(self,output, test):
		if ('won' not in output and 'Boo' not in output and 'ERROR' not in output and 'alive' not in output):
			logging.info(test);
			print(f"{TRED} It's NOK {ENDC}")
		else:
			print(f"{TGREEN} It's ok {ENDC}")

	def test(self):		
		for _ in range(self.nb_test):
			nb_player = random.randint(1, 4)
			cmd = 'timeout 30s ../corewar '
			for _ in range(nb_player):
				cmd += 'src/'
				cmd += self.files[random.randint(0, len(self.files) - 1)]
				cmd += ' '
			print(cmd)
			output = os.popen(cmd + '| tail -n 1').read();
			print(output)
			self.check_output(output, cmd)



segfault = Segfault(args[1])
segfault.test()
