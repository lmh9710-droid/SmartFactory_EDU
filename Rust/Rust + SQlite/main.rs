use rusqlite::{params, Connection, Result};

#[derive(Debug)]
struct User{
  id: i32,
  name: String,
  email:String,
}

fn main() -> Result<()>{

  let conn = Connection::open("database.db")?;

  conn.execute(
    "CREATE TABLE IF NOT EXISTS users (
            id    INTEGER PRIMARY KEY AUTOINCREMENT,
            name  TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE
        )",
        [],
  )?;

  println!("---테이블생성 완료---");

  create_user(&conn, "Kim", "Kim@email.com")?;
  create_user(&conn, "Lee", "Lee@email.com")?;
  println!("\n--- 데이터 삽입(create) 완료 ---\n");

  println!("\n---데이터 전체 조회(Read) ---");
  let users = read_all_users(&conn)?;
  
  for 
  }

  delete_user(&conn, 2)?;
  println!("\n---데이터 삭제(Delete) 완료 (ID 2번 삭제)---");


  update_user_email(&conn, 1, "kim@gmail.com");
  println!("유저 수저 완료");


  Ok(())
}

fn create_user(conn: &Connection, name: &str, email: &str) -> Result<()>{
  conn.execute("INSERT INTO users (name, email) VALUES (?1, ?2)",
            params![name, email],)?;
            Ok(())
}

fn read_all_users(conn: &Connection) -> Result<Vec<User>>{
  let mut stmt = conn.prepare("SELECT id, name, email FROM users")?;

  let user_iter = stmt.query_map([], |row| {
    Ok(User{
      id: row.get(0)?,
      name: row.get(1)?,
      email: row.get(2)?,
    })
  })?;

  let mut users = Vec::new(); //속이빈 벡터 메모리 할당
  for user in user_iter{
    users.push(user?);
  }
  Ok(users)
}

fn update_user_email(conn: &Connection, id: i32, new_email: &str)->Result<()>{
  let update_rows =conn.execute(
    "UPDATE users SET email = ?1 WHERE id = ?2",
    params![new_email, id],
  )?;

  if update_rows == 0 {
    println!("에러: 업데이트 안되었음");
  }

  Ok(())
}

fn delete_user(conn: &Connection, id: i32) -> Result<()> {
  conn.execute("DELETE FROM users WHERE id = ?1",
               params![id],)?;
    
    Ok(())

}
