---------------------- Data Types -----------------------------------------
-- Types start with uppercase letters, variables with lower case letters

-- list concatenation
a = [1,2,3] ++ [4,5]
-- strings are lists
b = "123" ++ "45"

-- define new data Types
-- Type Constructor (capital letter required)
data BookInfo = Book Int String [String]          -- is a 3-tuple (Int, String, [String])
                deriving (Show)                   -- needed for printing a value of this tpye
---------------------- Functions ------------------------------------------

-- Pattern matching
-- function argument should confirm a pattern
lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial (n - 1)

-- Guards
isOdd :: Int -> Bool
isOdd n
   | mod n 2 == 0 = False
   | otherwise = True

-- Where
batAvgRating :: Double -> Double -> String
batAvgRating hits atBats
   | avg <= 0.200 = "Terrible Batting Average"
   | avg <= 0.250 = "Average Player"
   | avg <= 0.280 = "You're doing pretty good"
   | otherwise = "You're a Superstart"
   where avg = hits / atBats

getListItems :: [Int] -> String
getListItems [] = "empty"
getListItems (x:[]) = "list starts with " ++ show x
getListItems (x:y:[]) = "list contains " ++ show x ++ " and " ++ show y
getListItems (x:xs) = "1st item is " ++ show x ++ " and the rest is " ++ show xs


-- Recursion
times4 :: Int -> Int
times4 x = x * 4

mulBy4 :: [Int] -> [Int]
mulBy4 [] = []
mulBy4 (x:xs) = times4 x : mulBy4 xs

-- Identity function (id() - build in version)
myI :: a -> a
myI a = a

-- higher order functions
listTimes4 :: [Int] -> [Int]
listTimes4 x = map times4 x

doMult :: (Int -> Int) -> Int
doMult func = func 3

num3Times4 = doMult times4

applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)
