import random,os
import winsound, shutil, enum
from pynput.keyboard import Key, Listener

def on_press(key):
    index = board.index("  ")
    if key == Key.up:
        up(index)
    elif key == Key.down:
        down(index)
    elif key == Key.left:
        left(index)
    elif key == Key.right:
        right(index)
    elif key == Key.esc:
        print()
        print("Game closed !!")
        return False
    else:
        print("Use arrow keys to play the game!\n")
        return
    print_board()

def is_end():
    return board == won_board

def beep(freq=5000, dur=100):
    winsound.Beep(freq, dur)

def start_game():
    random.shuffle(board)
    print_board()
    play_game()

def play_game():
    with Listener(on_press=on_press) as listener:
        listener.join()

def up(index):
    if index > size-1:
        board[index], board[index - size] = board[index - size], board[index]
    else:
        beep()

def down(index):
    if index < (size*size) - size:
        board[index], board[index + size] = board[index + size], board[index]
    else:
        beep()
    
def left(index):
    if (index % size) != 0:
        board[index], board[index-1] = board[index-1], board[index]
    else:
        beep()
    
def right(index):
    if (index - (size-1)) % size != 0:
        board[index], board[index+1] = board[index+1], board[index]
    else:
        beep()
    
def clear():
    os.system("cls")

def print_board():
    clear()
    print("\t\t\t-- SLIDING PUZZLE --\n")
    for i in range(size*size):
        if i % size == 0:
            print(f"\n\t\t\t{'------'*size}-")
            print(end="\t\t\t|  ")
        print(board[i],end="")
        if board[i] != "  " and board[i] < 10:
            print("  |  ",end="")
        else:
            print(" |  ",end="")
    print(f"\n\t\t\t{'------'*size}-")
    
    if is_end():
        print("\n YOU WON !!")
        exit()
    print("\n\t\t\tPress ESC to quit the game")


print("\nDifficulty level:")
print("1 => Easy   (3 x 3)")
print("2 => Medium (4 x 4)")
print("3 => Hard   (5 x 5)")
size = int(input("\nplease enter the difficulty level of game: "))
while size < 1 or size > 3:
    size = int(input("\nplease enter a proper choice: "))
size += 2
won_board = list(range(1, size*size)) + ["  "]
board = list(won_board)
start_game()