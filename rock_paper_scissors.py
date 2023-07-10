#Rock,Paper,scissors
import random

user_win=0
computer_win=0

options=["rock","paper","scissors"] #list implement in options

while True:
    user_input=input("Type Rock/Paper/Scissors or Q to quit:   ").lower()
    if(user_input=="q"):
        break
    if(user_input not in options):
        quit()
    random_number=random.randrange(0,2)
    computer_choice=options[random_number]
    #rock: 0    paper: 1    scissors: 2
    print("Computer choice: "+computer_choice+".")
    
    if user_input=="rock" and computer_choice=="scissor":
        print("Yon won!")
        user_win+=1
    elif user_input=="paper" and computer_choice=="rock":
        print("You won!")
        user_win+=1  
    elif user_input=="scissor"and computer_choice=="paper":
        print("You won!")
        user_win+=1
    elif user_input==computer_choice:
        print("Draw in this turn!")
    else:
        print("Computer win!")
        computer_win+=1
print("You won "+str(user_win)+" times.")
print("Computer won "+str(computer_win)+"times.")
print("Goodbye!")