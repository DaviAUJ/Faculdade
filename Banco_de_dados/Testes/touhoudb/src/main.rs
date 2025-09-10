use postgres::{Client, NoTls, Error};

fn main() -> Result<(), Error>{
    let client = Client::connect("postgres://postgres:postgres@localhost:5432/kappa", NoTls);

    for row in client?.query("SELECT * FROM touhou.characters", &[]) {
        let test = match row.get(1) {
            None => "",
            Some(value) => value.get(0)
        };

        println!("{}", test);
    }

    return Ok(())
}
