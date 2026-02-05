module Main(main) where

main :: IO()
main = do 
    putStrLn "digite uma frase:"
    frase <- getLine
    if reverse frase == frase 
        then putStrLn "eh palindrome" 
        else putStrLn "nao eh palindrome"