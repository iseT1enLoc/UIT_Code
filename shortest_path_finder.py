import curses 
from curses import wrapper
import queue
import time

maze=[
    ["#","#","#","#","#","#","#","#","#"],
    ["O"," "," "," "," "," "," "," ","#"],
    ["#"," ","#","#"," ","#","#"," ","#"],
    ["#"," ","#"," "," "," ","#"," ","#"],
    ["#"," ","#"," ","#"," ","#"," ","#"],
    ["#"," ","#"," ","#"," ","#"," ","#"],
    ["#"," ","#"," ","#"," ","#"," ","#"],
    ["#"," "," "," "," "," "," "," ","#"],
    ["#","#","#","#","#","#","#","#","#"],
]

def print_maze(maze,stdscr,path=[]):#path is default argument empty list so we dont need to pass it
    BLUE=curses.color_pair(1)
    RED=curses.color_pair(2)
    for i,row in enumerate(maze):
        for j, value in enumerate(row):
            if (i,j) in path:
              stdscr.addstr(i,j*2,"X",RED)
            else:
              stdscr.addstr(i,j*2,value,BLUE)

def find_start(maze,start):
    for i,row in enumerate(maze):
        for j, value in enumerate(row):
            if value==start:
                return i,j
    return None

def find_neighbors(maze,row,col):
    neighbors=[]
    
    if row>0:#UP
        neighbors.append((row-1,col))
    if row+1<len(maze):#DOWN
        neighbors.append((row+1,col))
    if col>0:#LEFT
        neighbors.append((row,col-1))
    if col+1<len(maze[0]):#RIGHT
        neighbors.append((row,col+1))
    
    return neighbors

def find_path(maze,stdscr):
    start="O"
    end="X"
    start_pos=find_start(maze,start) 
    
    q=queue.Queue()
    q.put((start_pos,[start_pos]))#tuple,list
    
    visited=set()
    
    while not q.empty():
        cur_pos,path=q.get()#cur_pos=start,path=[start_pos]
        row,col=cur_pos
        
        stdscr.clear()
        print_maze(maze,stdscr,path)
        time.sleep(0.2)
        stdscr.refresh()
        
        if maze[row][col]==end:
            return path
        
        neighbors=find_neighbors(maze,row,col)
        
        for neighbor in neighbors:
            if neighbor in visited:
                continue
            
            (r,c)=neighbor
            if maze[r][c]=="#":
                continue
            
            newpath=path+[neighbor]
            
            q.put((neighbor,newpath))
            visited.add(neighbor)
            
        

        
        
    
def main(stdscr):
    curses.init_pair(1,curses.COLOR_BLUE,curses.COLOR_BLACK)
    curses.init_pair(2,curses.COLOR_RED,curses.COLOR_BLACK)
    blue_and_black=curses.color_pair(1)
    find_path(maze,stdscr)
    stdscr.getch()#it is similar to an input statement, it wait here until we gonna hit something before we exit the program

wrapper(main)


    