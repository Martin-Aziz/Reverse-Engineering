pub struct Executer<'a> {
    pub program_name: String,
    interaction_logic: Option<&'a dyn Fn(Executer) -> ()>
}

impl<'a> Executer<'a> {
    pub fn new(name: String, interaction_logic: Option<&'a dyn Fn(Executer) -> ()>) -> Self {
        Self { program_name: name, interaction_logic }
    }
    pub fn go(self) -> Result<(), &'static str> {
        if let Some(f) = self.interaction_logic {
            f(self);
            return Ok(());
        }
        // TODO: Create default interaction logic maybe just interact with program over inherited stdio.
        Err("No default interaction logic implemented yet!")
    }
}