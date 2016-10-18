from sys import stdin, stdout

def main():
	for line in stdin:
		n = int(line)
		if(n==1):
			stdout.write(str(1)+"\n")
		else:
			stdout.write(str(2*n-2)+"\n")

if __name__ == "__main__":
	main()