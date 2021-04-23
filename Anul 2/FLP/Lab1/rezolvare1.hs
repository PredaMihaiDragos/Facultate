-- Limbajul unui mini calculator
data Prog = On Instr
data Instr = Off 
             | Expr :> Instr

data Expr = Mem 
            | V Int 
            | Expr :+ Expr

-- valoarea celulei de memorie
type Env = Int 

type DomProg = [Int]
type DomInstr = Env -> [Int]
type DomExpr = Env -> Int

-- Exercitiu - evaluare
prog :: Prog -> DomProg
prog (On instr) = stmt instr 0

-- stmt :: Instr -> Env = Int -> [Int]
stmt :: Instr -> DomInstr
stmt Off _ = []
stmt (exp :> instr) m = let
                          v = expr exp m
                        in
                          (v : (stmt instr v))

-- expr :: Expr -> Env = Int -> Int
expr :: Expr -> DomExpr
expr Mem m = m
expr (V val) _ = val
expr (exp1 :+ exp2) m = expr exp1 m + expr exp2 m

p1 = On ( (V 3) :> ((Mem :+ (V 5)) :> Off)) -- [3,8]
p2 = On ( (V 2) :> ((Mem :+ (V 5)) :> ((Mem :+ (V 1)) :> Off))) -- [2,7,8]
p3 = On ( (V 5) :> ((Mem :+ (V 4)) :> (((Mem :+ (V 3))) :> Off))) --[5,9,12]

val = On ((V 3) :> (( Mem :+ (V 5)) :> Off)) --[3,8]
val2 = On ((V 3) :> (( (V 7) :+ (V 5)) :> Off)) --[3,12]
val3 = On ((V 3) :> ( (V 7) :> (( Mem :+ (V 5)) :> Off))) --[3,7,12]
val4 = On ((V 3) :> ( (V 7) :> ( (V 6):> (( Mem :+ (V 5)) :> Off)))) --[3,7,6,11]


-- Mini-Haskell
type Name = String
data Hask = HTrue
            | HFalse
            | HLit Int
            | HIf Hask Hask Hask
            | Hask :==: Hask
            | Hask :+: Hask
            | HVar Name
            | HLam Name Hask
            | Hask :$: Hask
  deriving (Read, Show)
infix 4 :==:
infixl 6 :+:
infixl 9 :$:

data Value = VBool Bool
             | VInt Int
             | VFun (Value -> Value)
             | VError -- pentru reprezentarea erorilor

type HEnv = [(Name, Value)]
type DomHask = HEnv -> Value

-- a
instance Show Value where
  show (VBool b) = show b
  show (VInt i) = show i
  show (VFun f) = "<functie>"
  show VError = "<eroare>"

-- b
instance Eq Value where
  (VBool b1) == (VBool b2) = b1 == b2
  (VInt i1) == (VInt i2) = i1 == i2
  _ == _ = error "Nu se pot compara"

-- c
hEval :: Hask -> DomHask
hEval HTrue _ = VBool True
hEval HFalse _ = VBool False
hEval (HLit x) _ = VInt x
hEval (HIf condition first second) env
    | hEval condition env == VBool True = hEval first env
    | hEval condition env == VBool False = hEval second env
    | otherwise = hEval second env
