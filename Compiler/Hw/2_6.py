def trans(s,a):
    if a==1:
        if s==1:
            return 6
        elif s==2:
            return 3
        elif s==3:
            return 3
        elif s==4:
            return 7
        elif s==5:
            return 6
        elif s==6:
            return 7
        elif s==8:
            return 3
    elif a==0:
        if s==1:
            return 2
        elif s==2:
            return 7
        elif s==3:
            return 1
        elif s==4:
            return 3
        elif s==5:
            return 8
        elif s==6:
            return 3
        elif s==7:
            return 7
        elif s==8:
            return 7


nf0 = [1,2,4,5,6,7,8]
nf1 = []
nf2 = []
nf3 = []
nf4 = []
nf5 = []
nf6 = []
f = [3]
allset = [nf0,nf1,nf2,nf3,nf4,nf5,nf6,f]
for i in nf0:
    i0=i
    for j in nf0:
        j0=j
        if i0 != j0:
            while True:
                for x in [0,1]:
                    for y in [0,1]:
                        i,j=trans(i,x),trans(j,y)
                        for s1 in allset:
                            for s2 in allset:
                                if i in s1 and j in s2:
                                    if s1!=s2:
                                        nf0.remove(i0)
                                        for s_dst in allset:
                                            if len(s_dst)!=0:
                                                s_dst.append(i0)
                                                break
                                break
                            continue
                        continue
                    continue
                break


