# Importing Pyverilog classes/modules
from pyverilog.vparser.parser import VerilogParser
from pyverilog.vparser.preprocessor import VerilogPreprocessor



# Open the file in read mode
with open('your_file.txt', 'r') as file:
    # Read the content of the file
    file_content = file.read()

# Print the file content
print(file_content)
