--- Monada Identity


--- Limbajul si  Interpretorul
type M = Maybe

showM :: Show a => M a -> String
showM m = show m

type Name = String

data Term = Var Name
          | Con Integer
          | Term :+: Term
          | Lam Name Term
          | App Term Term
  deriving (Show)

pgm :: Term
pgm = App
  (Lam "y"
    (App
      (App
        (Lam "f"
          (Lam "y"
            (App (Var "f") (Var "y"))
          )
        )
        (Lam "x"
          (Var "x" :+: Var "y")
        )
      )
      (Con 3)
    )
  )
  (Con 4)


data Value = Num Integer
           | Fun (Value -> M Value)

instance Show Value where
 show (Num x) = show x
 show (Fun _) = "<function>"

type Environment = [(Name, Value)]

add :: Value -> Value -> M Value
add (Num x) (Num y) = return (Num (x+y))
add _ _ = Nothing

apply :: Value -> Value -> M Value
apply (Fun f) x = f x
apply _ _ = Nothing

interp :: Term -> Environment -> M Value
interp (Var name) env = case lookup name env of
    Just x -> return x
    Nothing -> Nothing
interp (Con a) _ = return (Num a)
interp (mx :+: my) env = do
    x <- interp mx env
    y <- interp my env
    add x y
interp (Lam x t) env = return $ Fun $ \v -> interp t ((x, v) : env)
interp (App mf mx) env = do
    f <- interp mf env
    x <- interp mx env
    apply f x


test :: Term -> String
test t = showM $ interp t []

pgm1:: Term
pgm1 = App
          (Lam "x" ((Var "x") :+: (Var "x")))
          ((Con 10) :+:  (Con 11))
-- test pgm
-- test pgm1
