#! /bin/python

import math
import random

BIT = 16

def MCD(a,b):
	t=0;
	if(b==0 or a==0):
		return 0
	if(a<b):
		t=b
		b=a
		a=t
	while(b != 0):
		t=b;
		b=a%b;
		a=t
		
	return a

def euclideEsteso(a, b):
    if b == 0:
        return (a, 1, 0)
    (d, ap, bp) = euclideEsteso(b , a%b)
    return (d, bp, ap - a/b * bp)

def inv_modulo(a,m):
    (d, x, ml) = euclideEsteso(a, m)
    if d == 1:
        return x % m
    return 0

def rootsGenerator(p):
	o = 1
	roots = range(p-1)
	for r in range(p-1):
		roots[r]=0
	z = 0
	for  r in range(2,p):
		k = (r**o)%p
		while (k > 1):
			o=o+1
			k = ((k%p) * (r%p))
		if (o == (p-1)) :
			roots[z] = r
			z=z+1
		o = 1
	return roots
	
def generatorFinder(p):
	if(p==2):
		return 1
	b = range(20)
	b = [0]*20
	counter = 0
	tofactorize = (p-1)

	while tofactorize%2 == 0:
		tofactorize = tofactorize/2
		b[0] = 2
	if b[0]!=0:
		counter = counter+1

	for i in range (1,20):
		t = pollardRho(tofactorize)
		if t not in b:
			b[i] = pollardRho(tofactorize)
			counter = counter+1
	a=2

	factors = range(counter)
	i=0
	for x in b:
		if x!=0:
			factors[i] = x
			i=i+1

	for c in range(p-1):
		for x in range(counter):
			res = (a**((p-1)/factors[x]))%p
			if res == 1:
				break
			if (x==counter-1):
				return a
		a = a+1
		
def pollardRho(N):
        if N%2==0:
                return 2
        x = random.randint(1, N-1)
        y = x
        c = random.randint(1, N-1)
        g = 1

        while g==1:             
                x = ((x*x)%N+c)%N
                y = ((y*y)%N+c)%N
                y = ((y*y)%N+c)%N
                g = MCD(abs(x-y),N)
	
        return g

def factorizebytwo(n):
	t=n
	if(n%2 == 0): 
		return [0,0,0,0]
	n = n-1
	i=0
	r=0
	while(n%2 == 0):
		n = n/2
		i=i+1
	return [t-1,2,i,n]

def millerRabin(p,t):
	if(p%2 == 0):
		return [0,p]

	fact = factorizebytwo(p)

	for i in range (0,t):
		a = random.randrange(2,p-2)
		y = (a**fact[3])
		y=y%p
		if (y != 1 and y!=p-1):
			j=1
			while (j<= fact[2] and y!=p-1):
				y=(y**2)%p
				if(y==1):
					return [0,p]
				j=j+1
			if(y != p-1):
				return [0,p]	
	return [1,p]

def generateLargePrimeNumber():
	x=[0,0]
	while(x[0]==0):
		x = millerRabin( random.randrange(10**3,10**4), 5 )
	return x

def generateElGamalRandomNumber(p):
	k=random.randrange(10**2,10**3)
	while(MCD(k,p-1)!=1):
		k=random.randrange(10**2,10**3)
	return k

def hashing(message):
	m = convertMessageBin(message)
	m = m + '0'*(BIT - (len(m)%BIT))
	numRighe = int(math.ceil(len(m)/float(BIT)))
	x = [[0 for i in range(BIT)] for i in range(numRighe)]
	result = range(BIT)
	tmp = '0'

	for riga in range(numRighe):
		x[riga] = m[BIT*riga:BIT*(riga+1)]
	
	for i in range(BIT):
		for riga in range(numRighe):
			tmp = int(tmp)  ^ int(x[riga][i]) 
		result[i]=int(tmp)

	k = int(''.join(str(i) for i in result))
	k = "0b"+str(k)
	k = hex(int(k,2))
	k=k.replace("0x",'')
	k=k.replace("L",'')
	return k

def convertMessageBin(m):
	l = m.encode("hex")
	l = bin(int(l,16))
	l = l.replace("0b",'')
	return l

def convertMessageDec(m):
	l = m.encode("hex")
	l = int(l,16)
	return l

def brent(N):
        if N%2==0:
                return 2
        y,c,m = random.randint(22, N-1),random.randint(23, N-1),random.randint(25, N-1)
        g,r,q = 1,1,1
        while g==1:             
                x = y
                for i in range(r):
                        y = ((y*y)%N+c)%N
                k = 0
                while (k<r and g==1):
                        ys = y
                        for i in range(min(m,r-k)):
                                y = ((y*y)%N+c)%N
                                q = q*(abs(x-y))%N
                        g = MCD(q,N)
                        k = k + m
                r = r*2
        if g==N:
                while True:
                        ys = ((ys*ys)%N+c)%N
                        g = MCD(abs(x-ys),N)
                        if g>1:
                                break        
        return g  

def computePublicKey():
	p = generateLargePrimeNumber()
	a = random.randrange(1,(p[1]-2))
	alfa = generatorFinder(p[1])
	beta = (alfa**a)%p[1]
	print "Public Key is: [ "+str(p[1])+" , "+str(alfa)+" , "+str(beta)+" ]"
	return [p[1],alfa,beta,a]

def signMessage(m,p,alfa,a,k):
	mess = hashing(m)
	mex = int(mess,16)%p
	r = (alfa**k)%p
	inversok = inv_modulo(k,p-1)
	s =  ( inversok * (mex- (a*r) ) )%(p-1) 
	print "Message Alice:\n"+m
	print "Message signed: ["+str(mess)+" , "+str(r)+" , "+str(s)+" ]\n"
	return[mex,r,s]

def checkSign(pk,sm):
	v1 =( ((pk[2]**sm[1]))%pk[0] * ((sm[1]**sm[2])%pk[0]) )%pk[0]
	v2 = ( pk[1]**sm[0] )%pk[0]
	if(v1==v2):
		print "Verification Sign"	

def crack(s1,s2,p,m1,m2,alfa,beta):
	print "\nAttempted cracking by Eve:\n" 
	y = MCD(s1[2]-s2[2],p-1)
	y=abs(y)
	mn1=int(hashing(m1),16)%p
	mn2=int(hashing(m2),16)%p
	x = inv_modulo( (s1[2]-s2[2])/y , (p-1)/y )
	k = x*((mn1-mn2)/y)%((p-1)/y)
	t=y-1
	if (alfa**k%p)==s1[1]:	
		print "Recovered K Value: "+str(k)	
	else:
		while(t!=0):
			value = ( k+(t*(p-1)/y) )%(p-1) 
			if (alfa**value%p)==s1[1]:
				print "Recovered K Value: "+str(value)	
				k=value
				break		
			t=t-1
	y =MCD(s1[1],p-1)
	y = abs(y)
	x = inv_modulo(s1[1]/y,(p-1)/y)
	a = x*((mn1-s1[2]*k)/y)%((p-1)/y)
	t=y-1
	if(alfa**a%p == beta):
		print "Recovered A Value: "+str(a)	
	else:
		while(t!=0):
			value = ( a+(t*(p-1)/y) )%(p-1) 
			if (alfa**value%p)==beta:
				print "Recovered A Value: "+str(value)	
				break	
			t=t-1
 
def crackHash(m):
	counter=0
	for i in range(len(m)):
		if m[i].isdigit():
			counter=counter+1
		else:
			counter = 0

		if (counter==3):
			break

	mex=range(len(m)+4)
	mex = m[:i]

	mex = mex + "0000"
	mex = mex + m[i:]
	return [hashing(mex),mex]
	
		


def init():
	pk = computePublicKey()
	print "A : "+str(pk[3])
	m1 = "It hereby agrees Bob is buying an old used bike does not work at a cost of 200 Euros , by the time xxx ."
	m2 = "Pending Confirmation"
	k = generateElGamalRandomNumber(pk[0])
	print "K Selected : "+str(k)+"\n"
	signed = signMessage(m1,pk[0],pk[1],pk[3],k)
	signed1 = signMessage(m2,pk[0],pk[1],pk[3],k)
	checkSign(pk,signed)
	checkSign(pk,signed1)
	print "\nAlice tries to fool Bob finding the same hash with a slightly different message :"
	ch = crackHash(m1)
	print "\nFound hash\""+ch[0]+"\" corresponding to \n"+ch[1]
	crack(signed,signed1,pk[0],m1,m2,pk[1],pk[2])
	

init()
	
