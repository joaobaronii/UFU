import System.Random
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

menu :: IO ()
menu = do
    putStrLn "1. Jogar"
    putStrLn "2. Recorde"
    putStrLn "3. Sair"
    putStr "Escolha uma opção: "
    opcao <- getLine
    case opcao of
        "1" -> jogar
        "2" -> mostrar
        "3" -> putStrLn "Obrigado por jogar!"
        _   -> putStrLn "Opção inválida. Tente novamente."

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Bem-vindo ao Jogo de Adivinhação!"
    menu

jogar :: IO ()
jogar = do
    aleatorio <- randomRIO (1, 100) :: IO Int
    putStrLn "Estou pensando em um número de 1 a 100."
    putStrLn "Tente advinhar."
    palpite aleatorio 1

palpite :: Int -> Int -> IO ()
palpite aleatorio tentativas = do
    putStr "Digite um número: "
    numero <- readLn
    if numero == aleatorio then do
        putStrLn  ("Parabéns! Você acertou em " ++ show tentativas ++ " tentativas.")
        atualizarrecorde tentativas
        jogarnovamente
    else if numero > aleatorio then do
        putStrLn ("Seu palpite de " ++ show numero ++ " é maior que o número correto.")
        palpite aleatorio (tentativas + 1)
    else do
        putStrLn ("Seu palpite de " ++ show numero ++ " é menor que o número correto.")
        palpite aleatorio (tentativas + 1)

jogarnovamente :: IO ()
jogarnovamente = do
    putStrLn "Deseja jogar novamente? (s para sim, qualquer outra coisa para sair): "
    op <- getLine
    case op of
        "s" -> jogar
        _   -> putStrLn "Obrigado por jogar o Jogo de Adivinhação!"

mostrar :: IO ()
mostrar = do
    recorde <- readFile "highscore.txt"
    putStrLn ("O recorde é: " ++ recorde)
    menu

atualizarrecorde :: Int -> IO ()
atualizarrecorde tentativas = do 
    antigo <- readFile "highscore.txt"
    if tentativas < read antigo 
        then do 
            putStrLn "Você bateu o recorde."
            writeFile "highscore.txt" (show tentativas)
        else putStrLn "Você não bateu o recorde."
