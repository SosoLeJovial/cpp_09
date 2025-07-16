```
	Ford-Johnson algorithm (Merge-Insertion Sort):



Step 1:

- Make pairs
- Sort pairs
- Repeat

```

a0 | b0 || a1 | b1...

15 | 3 || 19 | 7 || 1 | 12 || 21 | 5 || 20 | 8 || 2 | 11 || 18 | 9 || 4 | 16 || 14 | 6 || 17 | 10 || 13
3 | 15 || 7 | 19 || 1 | 12 || 5 | 21 || 8 | 20 || 2 | 11 || 9 | 18 || 4 | 16 || 6 | 14 || 10 | 17 || 13

3 15 | 7 19 || 1 12 | 5 21 || 8 20 | 2 11 || 9 18 | 4 16 || 6 14 | 10 17 || 13
3 15 | 7 19 || 1 12 | 5 21 || 2 11 | 8 20 || 4 16 | 9 18 || 6 14 | 10 17 || 13

3 15 7 19 | 1 12 5 21 || 2 11 8 20 | 4 16 9 18 || 6 14 10 17 | 13
3 15 7 19 | 1 12 5 21 || 4 16 9 18 | 2 11 8 20 || 6 14 10 17 | 13

3 15 7 19 1 12 5 21 | 4 16 9 18 2 11 8 20 || 6 14 10 17 13
4 16 9 18 2 11 8 20 | 3 15 7 19 1 12 5 21 || 6 14 10 17 13

```

Step 2:

- Place a0 b0...bN in main
- Place a1...aN in pend
- Place rest in rest
- Binary insert pend into main, use Jacobsthal indices to determine insertion points.
- Merge pairs
- Repeat

If jacobsthal, insert from right to left from the jacobsthal index (3, 5, 11, 21, 43, ...) minus the previous index.
ex:
```

1 | 6 | 3 | 4 | 10 | 9 | 7 | 8 | 5 | 13
3 | 4 | 10 | 9 | 7 | 8 | 5 | 13 (inserted first 2 (3-1) from right to left)
10 | 9 | 7 | 8 | 5 | 13 (inserted first 2 (5-3) from right to left)
(inserted first 6 (11-5) from right to left)

```

```

main:
a0 b0...bN
pend:
a1...aN
rest:

4 16 9 18 2 11 8 20 | 3 15 7 19 1 12 5 21 || 6 14 10 17 13

main:
4 16 9 18 2 11 8 20 | 3 15 7 19 1 12 5 21
pend:
rest:
6 14 10 17 13

---

4 16 9 18 | 2 11 8 20 || 3 15 7 19 | 1 12 5 21 || 6 14 10 17 | 13

main:
4 16 9 18 | 2 11 8 20 | 1 12 5 21
pend:
3 15 7 19 | 6 14 10 17
rest:
13

main:
6 14 10 17 | 4 16 9 18 | 3 15 7 19 | 2 11 8 20 | 1 12 5 21
pend:
rest:
13

---

6 14 | 10 17 || 4 16 | 9 18 || 3 15 | 7 19 || 2 11 | 8 20 || 1 12 | 5 21 || 13

main:
6 14 | 10 17 | 9 18 | 7 19 | 8 20 | 5 21
pend:
4 16 | 3 15 | 2 11 | 1 12
rest:
13

main:
2 11 | 1 12 | 6 14 | 3 15 | 4 16 | 10 17 | 9 18 | 7 19 | 8 20 | 5 21
pend:
rest:
13

---

2 | 11 || 1 | 12 || 6 | 14 || 3 | 15 || 4 | 16 || 10 | 17 || 9 | 18 || 7 | 19 || 8 | 20 || 5 | 21 || 13

main:
2 | 11 | 12 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21
pend:
1 | 6 | 3 | 4 | 10 | 9 | 7 | 8 | 5 | 13
rest:

main:
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21
pend:
rest:

```

```
