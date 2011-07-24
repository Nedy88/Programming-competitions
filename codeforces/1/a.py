width, height, size = map(int, raw_input().split())
horizontal = width / size
if width % size != 0:
    horizontal += 1
vertical = height / size
if height % size != 0:
    vertical += 1
print horizontal * vertical
