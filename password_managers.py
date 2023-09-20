from cryptography.fernet import Fernet



'''
def write_key():
    key=Fernet.generate_key()
    with open("key.key","wb") as key_file:
        key_file.write(key)'''

def load_key():
    file=open("key.key","rb")
    key=file.read()
    file.close()
    return key


master_pwd=input("What is the master password? ")
key=load_key()+master_pwd.encode()
fer=Fernet(key)

def view():
    with open("passwords.txt",'r') as f:
        for line in f.readlines():
            data=line.rstrip()
            user,passw=data.split('|')
            print("User: ",user,"| Password: ",fer.decrypt(passw.encode()).decode())
    
def add():
    name=input("Account name: ")
    pwd=input("Password: ")
    #some explanation and new knowledge
    #if we use "With" the file will automatically close as soon as you end up the operation
    #file=open("passwords.txt",'a') if we use this syntax we have to manually close the file file.close
    #a: append, r: read, w: write, override
    with  open("passwords.txt",'a') as f:
        f.write(name+"|"+fer.encrypt(pwd.encode()).decode()+'\n')
while True:
    mode=input("Would you like to add a new password or view the existing ones or press Q to exit: ").lower()
    if(mode=='q'):
        break
    if mode=="view":
        view()
    elif mode=="add":
        add()
    else:
        print("Invalid input!")
        continue
    