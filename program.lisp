42
()
'()

(quote (1 2 3 4 5))

(car '(4 9 16))
(cdr '(abc def))
(cdr '(abc . def))

(+)
(+ 10)
(+ 10 20)
(+ 10 20 50)

(-)
(- 10)
(- 10 30)
(- 10 20 50)

(*)
(* 10)
(* 10 20)
(* 10 20 50)

(cons (+ 2 3) (* 2 3))

((lambda (n) (* n n)) (+ 2 3))
((lambda (f x) (f (f x))) (lambda (n) (+ n 1)) 7)
