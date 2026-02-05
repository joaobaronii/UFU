-- Definindo o tipo de dados Student
data Student = Student StudentId FirstName LastName Age
                 deriving (Show)

type StudentId = Int
type FirstName = String
type LastName = String
type Age = Int 


initialDatabase :: [Student]
initialDatabase = []

addStudent :: Student -> [Student] -> IO [Student]
addStudent student database = do
    let updatedDatabase = student : database
    printDatabase updatedDatabase
    return updatedDatabase

printDatabase :: [Student] -> IO ()
printDatabase [] = return ()
printDatabase (student:students) = do
    printStudent student
    printDatabase students

printStudent :: Student -> IO ()
printStudent (Student sid fname lname age) =
    putStrLn $ "ID: " ++ show sid ++ ", Nome: " ++ fname ++ " " ++ lname ++ ", Idade: " ++ show age


findStudentById :: StudentId -> [Student] -> Student
findStudentById id database =
    case filter (\(Student sid _ _ _) -> sid == id) database of
        [] -> error "Estudante não encontrado"
        (student:_) -> student

-- Função para atualizar as informações de um estudante
updateStudent :: StudentId -> Student -> [Student] -> [Student]
updateStudent id newStudent database = do
    let updatedDatabase = map (\student@(Student sid _ _ _) -> if sid == id then newStudent else student) database
    updatedDatabase



-- Função para exibir o menu
menu :: [Student] -> IO ()
menu database = do
    putStrLn "1. Adicionar estudante"
    putStrLn "2. Recuperar estudante por ID"
    putStrLn "3. Atualizar informações do estudante"
    putStrLn "4. Sair"
    putStrLn "Escolha uma opção:"
    option <- getLine
    case option of
        "1" -> do
            putStrLn "Digite o ID do estudante:"
            studentId <- readLn
            putStrLn "Digite o primeiro nome do estudante:"
            firstName <- getLine
            putStrLn "Digite o sobrenome do estudante:"
            lastName <- getLine
            putStrLn "Digite a idade do estudante:"
            age <- readLn
            let newStudent = Student studentId firstName lastName age
            updatedDatabase <- addStudent newStudent database
            menu updatedDatabase
        "2" -> do
            putStrLn "Digite o ID do estudante:"
            studentId <- readLn
            printStudent (findStudentById studentId database)
            menu database
        "3" -> do
            putStrLn "Digite o ID do estudante que deseja atualizar:"
            studentId <- readLn
            putStrLn "Digite o novo primeiro nome do estudante:"
            newFirstName <- getLine
            putStrLn "Digite o novo sobrenome do estudante:"
            newLastName <- getLine
            putStrLn "Digite a nova idade do estudante:"
            newAge <- readLn
            let newStudent = Student studentId newFirstName newLastName newAge
            let updatedDatabase = updateStudent studentId newStudent database
            putStrLn "Informações do estudante atualizadas com sucesso."
            printDatabase updatedDatabase
            menu updatedDatabase
        "4" -> putStrLn "Saindo..."
        _ -> do
            putStrLn "Opção inválida."
            menu database

main :: IO ()
main = do
    putStrLn "Bem-vindo ao sistema de gerenciamento de estudantes."
    menu initialDatabase