from sys import stdin, stdout

def main():
	a=[None]*101;
	a[0]=1;
	a[1]=1;
	for i in range(2,101):
		a[i] = a[i-1]*i

	t=int(stdin.readline());
	while(t>0):
		n = int(stdin.readline());
		stdout.write(str(a[n])+"\n");
		t=t-1;

if __name__ == "__main__":
	main()