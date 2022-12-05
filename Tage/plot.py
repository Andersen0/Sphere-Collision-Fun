# opening the file in read mode
my_file = open("test.txt", "r")

# reading the file
data = my_file.read()

# replacing end of line('/n') with ' ' and
# splitting the text it further when '.' is seen.
data_into_list = data.replace('\n', ' ').split(".")

# printing the data
print(data_into_list)
my_file.close()