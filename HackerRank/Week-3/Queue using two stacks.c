# Enter your code here. Read input from STDIN. Print output to STDOUT
class quets:
    def __init__(self):
        self.sin=[]
        self.sout=[]
    
    def enq(self,a):
        self.sin.append(a)
    
    def deq(self):
        self._trans()
        return self.sout.pop()
    
    def pk(self):
        self._trans()
        return self.sout[-1]
        
    def _trans(self):
        if not self.sout:
            while self.sin:
                self.sout.append(self.sin.pop())


def main():
    m=int(input().strip())
    
    que=quets()
    out=[]
    for _ in range(m):
        quep=input().split()
        if quep[0]=='1':
            a=int(quep[1])
            que.enq(a)
        elif quep[0]=='2':
            que.deq()
        elif quep[0]=='3':
            out.append(str(que.pk()))
            
    print("\n".join(out))

if __name__ == "__main__":
    main()
        
    
        