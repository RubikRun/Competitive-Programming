import os

def get_file_content(file_name):
    with open(file_name, 'r') as f:
        return f.read()


def get_files_contents(file_names):
    files_contents = []
    for file_name in file_names:
        files_contents.append(get_file_content(file_name))
    return files_contents


def execute_and_return(program_name, input_file_name):
    print('Executing ' + input_file_name)
    return os.popen('./' + program_name + ' < ' + input_file_name).read()


    
#Reading input and output file names formats
path = input()
program_name = input()
inputs_format = input()
outputs_format = input()
#Getting all file names from working directory
os.chdir(path)
all_file_names = os.listdir(path)
#Finding input and output file names
input_file_names = []
output_file_names = []
for file_name in all_file_names:
    if file_name.endswith(inputs_format):
        input_file_names.append(file_name)
    elif file_name.endswith(outputs_format):
        output_file_names.append(file_name)
#Sorting input and output file names
input_file_names.sort()
output_file_names.sort()
#Getting correct outputs and strippin
correct_outputs = get_files_contents(output_file_names)
for i in range(len(correct_outputs)):
    correct_outputs[i] = correct_outputs[i].strip()
#Getting my outputs and strippin
my_outputs = []
for i in range(len(input_file_names)):
    my_outputs.append(execute_and_return(program_name, input_file_names[i]).strip())
#Checking
num_of_correct = 0
num_of_incorrect = 0
for i in range(len(my_outputs)):
    if my_outputs[i].strip() != correct_outputs[i].strip():
        num_of_incorrect += 1
        print('Failed ' + input_file_names[i][:-len(inputs_format)])
        #print('Your output: ' + my_outputs[i])
        #print('Correct output: ' + correct_outputs[i])
        print()
    else:
        num_of_correct += 1

print()
print()
print('-----------------------')
print(str(num_of_correct) + ' tests passed.')
print(str(num_of_incorrect) + ' tests failed.')
