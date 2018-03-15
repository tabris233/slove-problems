
def dayin(xs):
    print('--------------------------')
    print(xs)
    for x in xs:
        print(x)

if __name__ == '__main__':
    f = open('thoughtworks-in-1.txt')
    f2 = open('thoughtworks-in-2.txt')
    mmp , index = {},{}
    cnt = 0
    operator = f.read().split('\n')
    signal = map(int,f2.read().split('\n'))
    # dayin(operator)
    for x in operator:
        # print('++++++++++++:--',x)
        name = x.split()[0]
        coordinate = [int(xx) for xx in x.split()[1:]]
        # print('name',name)
        # print('coordinate',coordinate)
        if name not in mmp:
            if len(coordinate) == 3:
                mmp[name] = coordinate
                index[cnt] = ' '.join([name,str(cnt),str(mmp[name][0]),str(mmp[name][1]),str(mmp[name][2])])
            else: # elif len(coordinate) == 6:
                mmp[name] = 'Error'
                index[cnt] = 'Error: '+str(cnt)

        elif mmp[name] == 'Error':
            index[cnt] = 'Error: '+str(cnt)
            continue
        elif len(coordinate) == 3:
            mmp[name] = 'Error'
            index[cnt] = 'Error: '+str(cnt)
        else:
            if(mmp[name][0] == coordinate[0] and mmp[name][1] == coordinate[1] and mmp[name][2] == coordinate[2]):
                mmp[name][0] = coordinate[0]+coordinate[3] 
                mmp[name][1] = coordinate[1]+coordinate[4] 
                mmp[name][2] = coordinate[2]+coordinate[5]
                index[cnt] = ' '.join([name,str(cnt),str(mmp[name][0]),str(mmp[name][1]),str(mmp[name][2])])
            else:
                mmp[name] = 'Error'
                index[cnt] = 'Error: '+str(cnt)
        cnt += 1

    # print(mmp)

    # dayin(signal)
    # print('cnt = ',cnt)
    # print(signal)
    for x in signal:
        # print('signal ---> ',x)
        if x > cnt:
            print('Cannot find',x)
        else:
            print(index[x])
    # print('END THE CODE')
