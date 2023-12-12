# Code Repository and Notebook Generator for ICPC and Similar Contests

To generate the notebook using [codes2pdf](https://github.com/Erfaniaa/codes2pdf), run:

```plaintext
codes2pdf <source_dir> [options]

Auto generate a PDF notebook from your source codes

Options:

    -V, --version             output the version number
    -a --author [name]        author's name to be added in the notebook
    -i --initials [initials]  initials of the author to be placed in the upper-right corner of all pages
    -o --output [filename]    output file for the notebook. Default to `./notebook.pdf`
    -h, --help                output usage information
```

Exampe:

```sh
# codes2pdf is a Node.js module
npx codes2pdf ./ /tmp/team_reference.pdf
npx codes2pdf ./src --author "NSU\_TravelingSolvesmen" --initials "NSU"
```


https://vscode.dev/tunnel/lib612-hp-elitedesk-/home/nadman
