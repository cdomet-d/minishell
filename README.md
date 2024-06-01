
# Minishell

Minishell is a project of the 42 Common Core. It aims to create a basic version of a Bash, capable of executing commands, handling redirections and signals, and implementing common built-in commands.

## Features
- Single and double quotes interpretation and removal
- Input tokenisation
- Variable substitution
- Executing Bash binaries and builtins (cd, echo, pwd, export, unset, exit, env), alone or in pipelines with absolute and relative paths
- Recreation of said builtin commands,  
- Redirections handling (<, >, <<, >>)
- Handling of $? operator to display pipelines return values
- Custom signal handling (SIGINT, SIQUIT, SIGPIPE)
## Technologies Used
- Language: C
- Valgrind
- Library: readline



## Installation

```bash
git clone https://github.com/Jauppp/minishell.git minishell
cd minishell
make

```
To run Minishell with Valgrind (with Readline && Bash supression):
```bash
make run
```

## References

- [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
- [Understanding Shell Expansion](https://effective-shell.com/part-6-advanced-techniques/understanding-shell-expansion/)
- [Readline Documentation](https://www.man7.org/linux/man-pages/man3/readline.3.html)



## Authors

- [@csweetin](https://github.com/cha202)
- [@cdomet-d](https://github.com/Jauppp)


# Appendix

## Execution loop logic graph

```mermaid
%%{init: {'theme': 'neutral', 'themeVariables': {'fontFamily': 'Arial', 'fontSize': '14px'}, 'flowchart': {'curve': 'linear'}}}%%
graph TD;

    %% Start of the process
    A(Start Process) --> B(create_hdocs);

    %% Loop for input handling
    B --> C(Is input null?);
    
    %% Handling input
    C -->|No| D(Is input a single builtin?);
    C -->|Yes| Q(End Process);
    
    %% Builtin command handling
    D -->|Yes| E(Execute builtin in parent);
    D -->|No| F(Create child process);
    
    %% Execution in parent or child
    E --> F;
    F --> G(In child process);
    
    %% Child process handling
    G -->|Yes| H(Redirect command) --> a.0
    H -->|No| J("End process if 
				command was invalid" ) --> K("Save current 
					pipe read end");

    a.0(Is pipe redirection) --> |Yes| b.0(Perform pipe redirection);
    a.0(Is pipe redirection) --> |No| c.00(Perform pipe redirection);
    b.0 --> c.00(Is <, >, << or >>)
	c.00 --> |Yes| c.01(Perform file redirection);
	c.00 --> |No| d.0(Perform file redirection);
    c.01 --> d.0(Execute command);
    d.0 --> g.0(Set exit status);
	g.0 --> J

    %% Loop continuation
    K --> V(Find next pipe) --> C;
    
    %% End of process
    Q --> R(Wait for children) --> S("Set exit status 
		of last child");
```
```mermaid
%%{init: {'theme': 'neutral', 'themeVariables': {'fontFamily': 'Arial', 'fontSize': '14px'}, 'flowchart': {'curve': 'linear'}}}%%
graph TD
STR(str) --> |<, >, >>| redir(op) --> |"(whitespace +) ascii char \nexcept <, >, <<, >>, | if not in quotes"| file(file)
redir --> |"whitespace, op or nothing"| redirerror("syntax error")
file --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| redircmd(cmd)
redircmd --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| rao(arg /opt)
redircmd --> redirophd
rao --> redirophd
file --> redirophd(op /hd) --> redirdot(...)

STR --> |"pipe"| pip(op) --> A("op /hd /cmd /nothing") --> pipeerror("syntax error")
STR --> dost(...) --> |"pipe"| pipe(op)
pipe --> |"whitespace or nothing"| pipeerror
pipe --> |"(whitespace +) ascii char \nexcept <, >, <<, >>, | if not in quotes"| pipecmd(cmd)
pipe --> op/hd(op /hd)
pipecmd --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| pao(arg /opt)
pao --> op/hd
pipecmd --> op/hd
op/hd --> dot(...)

STR --> |<<| hd(heredoc)
hd --> |"whitespace, op or nothing"| hderror("syntax error")
hd --> |"(whitespace +) ascii char \nexcept <, >, <<, >>, | if not in quotes"| delim(delim)
delim --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| hdcmd(cmd) --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| hdcmdopt(arg /opt)
delim --> hdop(op /hd)
hdcmd --> hdop
hdcmdopt --> hdop
hdop --> hdodt(...)

STR --> |"(whitespace +) ascii char \nexcept <, >, <<, >>, | if not in quotes"| cmd(cmd) 
cmd --> |"whitespace + ascii char \nexcept <, >, <<, >>, | if not in quotes"| cmdopt(arg /opt)
cmd --> cmdop(op /hd)
cmdopt --> cmdop(op /hd)
cmdop --> cmddot(...)
```

## File tree
```
Makefile
README.md
includes/
├── exec.h
├── libft
├── minishell.h
└── parsing.h
utils/
├── exec.md
└── supp.supp
scripts	/
├── exf
├── extract_funct
├── prep
└── push	
src/
├── main.c
├── builtins/
│   ├── bt_functs/
│   │   ├── builtin_utils.c	
│   │   ├── echo.c
│   │   ├── cd.c 
│   │   ├── cd_canon_form.c	
│   │   ├── cd_utils.c
│   │   ├── env.c	
│   │   ├── exit.c
│   │   ├── export.c	
│   │   ├── export_utils.c
│   │   ├── pwd.c	
│   │   └── unset.c
│   ├── exec_builtins.c
│   └── exec_builtins_utils.c
├── exec/
│   ├── utils/
│   │   ├── arenvlst.c	
│   │   ├── fd_handling.c	
│   │   ├── exec_utils.c	
│   │   ├── operators_utils.c
│   │   └── redirection_utils.c
│   ├── exec.c	
│   ├── exec_errors.c	
│   └── redirections.c
├── heredoc/
│   ├── heredoc.c	
│   ├── heredoc_errors.c
│   ├── heredoc_expand.c	
│   └── heredoc_utils.c
├── lst_utils/
│   ├── env_lst_utils.c
│   └── input_lst_utils.c
├── parsing/
│   ├── expansion/
│   │   ├── expand.c	
│   │   ├── expand_split.c
│   │   ├── expand_split_utils.c	
│   │   └── expand_utils.c
│   ├── tokenization/
│   │   ├── cmd_opt.c	
│   │   ├── create_data.c
│   │   ├── tokenization.c	
│   │   ├── tokenization_utils.c	
│   │   └── toke_type.c
│   ├── cmd_path.c	
│   ├── cmd_path_utils.c
│   ├── create_lst.c	
│   ├── parsing.c
│   ├── rm_quotes.c	
│   └── toke_builtin.c
├── signals/
│   ├── sighandler.c
│   └── sig_set_stat.c
└── utils/
    └── error_handling.c
```
