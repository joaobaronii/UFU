module Main(main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do 
        hSetBuffering stdout NoBuffering
        putStrLn "1. salvar uma frase em um arquivo"
        putStrLn "2. imprimir conteudo do arquivo"
        putStrLn "3. sair"
        putStr "escolha uma opcao: "
        o <- readLn
        case o of
                  1 -> do 
                       frase <- getLine
                       writeFile "6.txt" frase
                       putStrLn " "
                       main
                  2 -> do 
                       conteudo <- readFile "6.txt"
                       putStrLn conteudo
                       putStrLn " "
                       main
                  3 -> do 
                       putStrLn "saindo"
                  _ -> do 
                       putStrLn "opcao invalida"