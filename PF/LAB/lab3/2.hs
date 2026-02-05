module Main(main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do hSetBuffering stdout NoBuffering
        putStrLn "digite tres numeros"
        a <- getLine
        b <- getLine
        c <- getLine
        putStr "multiplicacao dos numeros: "
        putStrLn (show (read a * read b * read c :: Float)) 