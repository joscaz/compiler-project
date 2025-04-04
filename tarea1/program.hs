-- Author: Jose Zertuche
-- First time interacting with the language

----------------- STACK -----------------
-- Declare custom data type
-- EmptyStack used as a constructor for empty stack
-- Stack [a] used as constructor wrapping a list of [a] ('a' could be any type)
-- Show allows to print values
-- Eq allows to make comparisons
data Stack a = EmptyStack | Stack [a] deriving (Show, Eq)

-- Pushing element to stack
push :: a -> Stack a -> Stack a
-- if stack empty, create a new one containing only [x]
push x EmptyStack = Stack [x]
-- if stack not empty, we add x to the front of the list
push x (Stack xs) = Stack (x : xs)

-- Popping element from stack
pop :: Stack a -> (Maybe a, Stack a) -- returns tuple with the popped elem, and the stack after removal
-- case 1: if empty stack, return nothing
pop EmptyStack = (Nothing, EmptyStack)
-- case 2: if not empty, then pop the element
-- if stack contains elements x:xs, return only the x (top)
-- and the new stack without x
pop (Stack (x:xs)) = (Just x, Stack xs)
-- added case for empty list
pop (Stack []) = (Nothing, EmptyStack)



----------------- QUEUE -----------------
-- [a] [a] because the front list and the rear of list
data Queue a = Queue [a] [a] deriving (Show, Eq)

-- when removing from front list list might end up with an empty list even though
-- we have elems at the rear
checkQueue :: Queue a -> Queue a
-- EDGE CASE found after hours of debugging
-- if front list empty, we reverse the rear list 'ys' to maintain FIFO property
-- rear becomes empty after
checkQueue (Queue [] ys) = Queue (reverse ys) []
-- queue returned
checkQueue q = q

-- Enqueue method (adding)
-- definition of this is
enqueue :: a -> Queue a -> Queue a
-- Check with checkQueue and add 'x' to beginning of rear list
enqueue x (Queue front rear) = checkQueue (Queue front (x:rear))

-- Dequeue method (popping)
dequeue :: Queue a -> (Maybe a, Queue a)
-- if queue empty return nothing and empty queue
dequeue (Queue [] [] ) = (Nothing, Queue [] [])
-- if there is something in front, remove first elem from front ('x')
-- return the popped elem, and the new queue
dequeue (Queue (x:xs) ys) = (Just x, checkQueue (Queue xs ys))


----------------- DICTIONARY -----------------
-- two params: k as key, v as value
data Dict k v = Dict [(k, v)] deriving (Show, Eq)

-- insert to the dict
-- Eq k means that key 'k' needs to support equality testing (its a constraint)
-- insert takes key value and adds it to Dict and insert returns a Dict with k v
insert :: (Eq k) => k -> v -> Dict k v -> Dict k v
-- add new k,v to front of list
-- we use the filter with a method I saw online to make sure
-- that we remove any duplicate keys
insert key value (Dict xs) = Dict ((key, value) : filter (\(k, _) -> k /= key) xs)

-- searching for a key
-- parameter k that we pass to a Dict and we return the value
searchDict :: (Eq k) => k -> Dict k v -> Maybe v
-- lookup is a built-in Haskell function that takes a key and a list of pairs
-- and returns the value if present, if not returns nothing
searchDict key (Dict xs) = lookup key xs

-- remove a key
remove :: (Eq k) => k -> Dict k v -> Dict k v
-- remove the pair which key matches the one we want to remove
-- i searched for this online and based on it
remove key (Dict xs) = Dict (filter (\(k, _) -> k /= key) xs)

-- Program execution
main :: IO ()
main = do
    putStrLn "----- Stack -----"
    let s1 = EmptyStack
    let s2 = push 1 s1
    let s3 = push 2 s2
    let s4 = push 3 s3

    print s4

    let (top1, s5) = pop s4 -- top1 popped elem, s5 stack after pop
    print top1
    print s5

    let (top2, s6) = pop s5
    print top2
    print s6

    let (top3, s7) = pop s6
    print top3
    print s7   -- should return EmptyStack

    let (top4, s8) = pop s7
    print top4 -- top4 is nothing here
    print s8   -- EmptyStack

    putStrLn "----- Queue -----"
    let q1 = Queue [] []
    let q2 = enqueue 1 q1
    let q3 = enqueue 2 q2
    let q4 = enqueue 3 q3

    print q4 -- the queue should look like [1,2,3] []

    let (front1, q5) = dequeue q4
    print front1
    print q5

    let (front2, q6) = dequeue q5
    print front2
    print q6

    let (front3, q7) = dequeue q6
    print front3
    print q7 -- q is like [] []

    let (front4, q8) = dequeue q7
    print front4  -- nothing
    print q8      -- queue [] []


    putStrLn "----- Dictionary -----"
    let d1 = Dict []
    let d2 = insert "david" 4 d1
    let d3 = insert "jose" 2 d2
    let d4 = insert "carlos" 7 d3
    let d5 = insert "jose" 3 d4 -- here we override value for key 'jose'

    print d5

    print (searchDict "jose" d5)
    print (searchDict "david" d5)
    print (searchDict "carlos" d5)

    let d6 = remove "jose" d5
    print d6
