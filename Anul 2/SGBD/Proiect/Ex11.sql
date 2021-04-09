-- Trigger care in momentul in care un user isi confirma contul, ii adauga rolul de utilizator si ii seteaza numarul de lectii la 0.

CREATE OR REPLACE TRIGGER ADD_REFERRAL_TRIGGER 
BEFORE UPDATE ON users
FOR EACH ROW
DECLARE
BEGIN
  IF :OLD.confirmed_at IS NULL AND :NEW.confirmed_at IS NOT NULL
  THEN
    INSERT INTO roles_users(users_id, role_id)
    VALUES(:NEW.id, (SELECT id 
                           FROM role
                           WHERE name = 'Utilizator'));
                    
    
    :NEW.lessons := 0;
  END IF;
END;
/

INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (11, 'testmail@test.com', 'Test nume', 'testpassword', 0, 0, null, 1, '071234567');
        
UPDATE users
SET confirmed_at = TO_DATE('2020-03-15', 'yyyy-mm-dd')
WHERE id = 11;
