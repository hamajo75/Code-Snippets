: factorial ( n -- result )
  1 swap 1 do i 1+ * loop ;

." 10! is "
10 factorial .
CR ( Linebreak. This is a comment by the way.)
