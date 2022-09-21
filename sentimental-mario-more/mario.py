while True:
    try:
        h = int(input('Height: '))
        break
    except:
        pass
for i in range(1, h+1):
    print(f'{"#"*i : >{h}}  {"#"*i}')