; output
(format t "Hello, World!~%")                                                   ; % - newline

; call function
(format t "~a~%"                                                               ; ~a aestetic - human readable
  (+ 2 3)
)

(format t "~a~%"
  '(+ 2 3)                                                                     ; '() don't eval
)
