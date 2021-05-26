(define VARIANT 11)
(define LAST-DIGIT-OF-GROUP-NUMBER 6)
(define KINDS-OF-COINS 5)

(define (first-denomination kinds-of-coins)
  (if (= kinds-of-coins 1)
      1
      (if (= kinds-of-coins 2)
          2
          (if (= kinds-of-coins 3)
              3
              (if (= kinds-of-coins 4)
                  10
                  (if (= kinds-of-coins 5)
                      15
                      0
                      )
                  )
              )
          )
      )
  )

(define (count-change amount)
  (display "______\n amount: ")
  (display amount)
  (newline)
  (display "KINDS-OF-COINS: ")
  (display KINDS-OF-COINS)
  (newline)
  (let( (largest-coin (first-denomination KINDS-OF-COINS)) )
    (display "largest-coin: ")
    (display largest-coin)
    (newline)
    (if (and (not (<= amount 0)) (not (<= KINDS-OF-COINS 0)) (not (<= largest-coin 0)))
        (let()
          (display "List of coin denominations: ")
          (denomination-list KINDS-OF-COINS)
          (display "count-change= ")
          (cc amount KINDS-OF-COINS)
          )
        (let()
          (display "Improper parameter value!\ncount-change= ")
           -1
          )
        )
  )
)

(define (pier? x? y?)
  (and(not x?)(not y?))
)
  
(define (cc amount kinds-of-coins)
  (if (= amount 0)
      1
      (if (pier? (and (<= amount 0) (not (= amount 0))) (= kinds-of-coins 0))
          (+ (cc amount (- kinds-of-coins 1)) (cc (- amount (first-denomination kinds-of-coins)) kinds-of-coins))
          0
          )
      )
)

(define (denomination-list kinds-of-coins)
  (if (= kinds-of-coins 0)
      (let() (newline) 0)
      (let() (display (first-denomination kinds-of-coins)) (display " ") (denomination-list ( - kinds-of-coins 1)))
      )
)

(define (GR-AMOUNT) (remainder (+ (* 100 LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 231))

(display "Variant ")
(display VARIANT)
(newline)
(newline)
(display (count-change 100))
(newline)
(display (count-change (GR-AMOUNT)))
(newline)
(set! KINDS-OF-COINS 13)
(display (count-change 100))
(newline)
(display "(c) Ilin I.O. 2021\n")
