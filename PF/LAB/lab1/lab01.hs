dobro :: Num a => a -> a
dobro x = 2 * x

quadriplicar x = dobro (dobro x)

soma2 :: Num a => a -> a -> a
soma2 x y = x + y

soma4 :: Num a => a -> a -> a -> a -> a
soma4 a b c d = a + b + c + d

misterio x y z w = soma2 (soma2 x y) (soma2 z w)

hipotenusa :: Floating a => a -> a -> a
hipotenusa c1 c2 = sqrt (c1^2 + c2^2)