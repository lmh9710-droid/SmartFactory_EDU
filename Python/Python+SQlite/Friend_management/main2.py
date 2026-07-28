import menu as mn
DB_PATH = 'friends2.db'

if __name__ =="__main__":
   while(1): 
    me = mn.menuDisplay(DB_PATH)
    me.print_menu()
    if(me.run() == 0):
      break
