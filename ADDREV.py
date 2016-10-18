from sys import stdin, stdout

def main():
	t=int(stdin.readline())
	while(t>0):
		t=t-1
		a,b=stdin.readline().split()
		a=a[::-1]
		b=b[::-1]
		ans = int(str(int(a)+int(b))[::-1])
		stdout.write(str(ans)+"\n")

if __name__ == "__main__":
	main()