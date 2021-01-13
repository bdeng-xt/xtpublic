import math 
import os,sys 


def is_prime(num):
    if num<=1:
        return False 
    if (num%2)==0 or (num%3)==0:
        return True 
    i=5
    while (i*i)<=num:
        if (num%i)==0 or (num%(i+2))==0:
            return False
        i=i+6
    return True 
def calc_gcd(a,b):
    '''
    better to use math.gcd(a,b)
    '''
    if a==0:
        return b 
    if b==0:
        return a 
    if a>b:
        return calc_gcd(a%b,b)
    elif a<b:
        return calc_gcd(a,b%a)
    else:
        return a
def calc_comb(n,k):
    '''
    n choose k
    '''
    if k>n:
        return 0
    if k==0 or k==n:
        return 1
    return calc_comb(n-1,k-1)+calc_comb(n-1,k-1)
def calc_prime_factors(n):
    factors = []
    def get_factor(n):
        x_fixed = 2
        cycle_size = 2
        x = 2
        factor = 1
        while factor == 1:
            for count in range(cycle_size):
                if factor > 1: break
                x = (x * x + 1) % n
                factor = math.gcd(x - x_fixed, n)
            cycle_size *= 2
            x_fixed = x
        return factor
    while n > 1:
        next = get_factor(n)
        factors.append(next)
        n //= next
    return factors
def calc_digit_sum(n):
    num=n
    r=num%10
    num=num//10
    result=r
    while (num>0):
        r=num%10
        num=num//10
        result=result+r
    return result
def get_prime_factors(n):
    num=n
    if num<=1:
        return []
    result=[]
    while (num%2)==0:
        result.append(2)
        num=num//2
    while (num%3)==0:
        result.append(3)
        num=num//3
    upper=math.ceil(math.sqrt(n))
    for i in range(5,upper,6):
        if num<i:
            break
        while (num%i)==0:
            result.append(i)
            num=num//i
        while (num%(i+2))==0:
            result.append(i+2)
            num=num//(i+2)
    if num>3:
        result.append(num)
    return result        