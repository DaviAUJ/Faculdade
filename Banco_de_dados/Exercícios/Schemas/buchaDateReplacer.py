import re;

def dashrepl(matchobj):
    return f"{matchobj.group(0)}/{matchobj.group(1)}/{matchobj.group(2)}"

file = open("hospital-schema.sql", "r");
write = open("teste.sql", "w");
text = file.read();

write.write(re.sub(r"(\d{2})-(\d{2})-(\d{4})", r"\3/\1/\2", text));

file.close();
write.close();
