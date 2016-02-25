import zipfile

zip_file = zipfile.ZipFile('brute.zip')
output_verbose = 1  # increase that for long password list
with open('passwords.txt', 'rb') as password_list:
    for line in password_list:
        try:
            pwd = line.strip(b'\n')
            zip_file.extractall(pwd=pwd)
        except RuntimeError:
            #if index % output_verbose == 0:
            print('The {} word not matched.'.format( pwd))
        else:
            print('Wow ! found the password: {}'.format( pwd))
            break

zip_file.close()
