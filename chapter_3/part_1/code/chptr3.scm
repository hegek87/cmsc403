#lang scheme
;3.8 (a)
; Find the length of an arbitrary list using tail recursion
(define (length list)
  (length-tail list 0))

(define (length-tail list count)
  (if (null? list)
      count
      (length-tail (cdr list) (+ count 1))))

;(length (list 1 2 3 4 5 6 7))

; 3.8 (b)
(define (find-min list min)
  (if (null? list) 
      min
      (if (< (car list) min)
          (find-min (cdr list) (car list))
          (find-min (cdr list) min))))

(define (find-max list max)
  (if (null? list)
      max
      (if (> (car list) max)
          (find-max (cdr list) (car list))
          (find-max (cdr list) max))))

(define (find-max-min list)
  (cons (find-min list (car list))
        (find-max list (car list))))

;(find-max-min (list 10 54 13 45 14 643 74 23))

; 3.8 (c)
(define (read-list)
  (let ((x (string->number (read-line))))
    (if (= x 0)
        null
        (cons x (read-list)))))

;(read-list)

; 3.8 (d)
(define (find-max-min-input)
  (find-max-min (read-list)))
;(find-max-min-input)



; 3.8 (e)
;; quicksort : list -> list
; pseudo code:
; if list.size = 1 or list==null, return it
; find pivot
; combine (quicksort front), pivot el, (quicksort bac)
(define (quicksort lst)
  ;; pivot : int, list, list, list -> list, list
  (define (pivot piv plst front back)
    (cond ((null? plst) (cons front back))
          ((< (car plst) piv)
           (pivot piv (cdr plst) (cons (car plst) front) back))
          (else
           (pivot piv (cdr plst) front (cons (car plst) back)))))
  ;; combine : int, list, list, acc -> list
  ;; we are assuming each el in front < el in back
  (define (combine piv front back)
    (if (null? front)
        (cons piv back)
        (cons (car front)
              (combine piv (cdr front) back))))
  (if (or (null? lst) (null? (cdr lst)))
      lst
      ((lambda (x)
         (combine (car lst)
                  (quicksort (car x))
                  (quicksort (cdr x))))
       (pivot (car lst) (cdr lst) '() '()))))
(quicksort (list 54 87 514 574 154 78 32 65 98 151 25 63 48596 25 31))
        

; 3.8 (f)
;; split(list)
;; return a 2-tuple with the halves of the list in it
; find list length - this is fine since it is O(n) < O(log n)
; build first half, return rest
(define (split lst)
  (define (split-list lst n cur front)
    (if (>= cur n)
        (cons front lst)
        (split-list (cdr lst) n (+ cur 1) (cons (car lst) front))))
  (split-list lst (/ (length lst) 2) 0 '()))
;(split (list 14 7 1 2 1))

;; mergelist : list,list -> list
; Given two sorted lists, merge them
(define (mergelist front back)
  (cond ((null? front) back)
        ((null? back) front)
        ;; if the first el in front > first el in back
        ;; put el from back into the list
        ((> (car front) (car back))
         (cons (car back)
               (mergelist front (cdr back))))
        ;; otherwise put the first el in front into the list
        (else 
         (cons (car front)
               (mergelist (cdr front) back)))))
;(mergelist (list 1 12 17 20 22) (list 1 3 8 10 17 19 20))
;(1,2,3,4,5,6)

;; merge sort
;; high level design (pseudo-code version)
; mergesort(list)
; if the list is small, return it
; split the list in half
; merge the two lists
(define (mergesort lst)
  (cond ((null? lst) '())
        ((= (length lst) 1) lst)
        (else
         ((lambda (x)
            (mergelist (mergesort (car x))
                       (mergesort (cdr x))))
         (split lst)))))

(mergesort (list 76 67 9 587 7 5 87 65 8 54 8))


  
;  (let ((x (/ (length lst) 2)))
;    (display x)))
;(split (list 1 2 3 4))

; 3.8 (g)
(define (is-pyth a b c)
  (if (= (+ (* a a) (* b b)) (* c c))
      true
      false))

(define (display-triple a b c)
  (display a)
  (display ", ")
  (display b)
  (display ", ")
  (display c)
  (newline))

;; (1,1,1),(1,1,2),(1,1,3),(1,1,4),...,(1,1,n)
;; (1,2,2),(1,2,3),(1,2,4),(1,2,5),...,(1,2,n)
;; ...
;; (1,n n)
;; (2,2,2),(2,2,3),(2,2,4),...,(2,2,n)
;; (2,3,3),(2,3,4),(2,3,5),...,(2,3,n)
(define (get-pythagorean n)
  ;; loop a from 1 to n
  (do ((a 1 (+ a 1)))
    ((> a n))
    ;; loop from a to n
    (do ((b a (+ b 1)))
      ((> b n))
      ;; loop from b to n
      (do ((c b (+ c 1)))
        ((> c n))
        ;; if a^2+b^2=c^2, print (a,b,c)
        (when (is-pyth a b c)
          (display-triple a b c))))))
  
(get-pythagorean 35)
;(is-pyth 3 4 5)
        
  
; 3.8 (h)
(define (twice f)
  (lambda (x)
    (f (f x))))

(define (square x) (* x x))
;; computes the number x^4
;((twice(twice square)) 3)

; 3.8 (i)
(define (inc_n x)
  (lambda (y)
    (+ x y)))
;((inc_n -2) 3)