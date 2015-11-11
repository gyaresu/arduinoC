key = '10101010'
result = ''

for k in key:
        x = "*"
        if(k == "0"):
         x = "1110" # <mossmann> A zero is encoded as a longer high pulse (high-high-low)
        if(k == "1"):
         x = "1100" #<mossmann> and a one is encoded as a shorter high pulse (high-low-low).
        if(k == "x"):
         x = "0000" #<mossmann> AndrewMac: Maybe the transmitter is slow to warm up to maximum power?  What happens if you add some zero padding at the start?
        result += x

print result
