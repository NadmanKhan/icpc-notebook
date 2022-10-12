import * as cheerio from 'cheerio';
import * as fs from 'fs';

const html = fs.readFileSync(__dirname + '/equations.html').toString();
const $ = cheerio.load(html);

const parseContents = (node: cheerio.AnyNode): string => {
    let res = '';
    $(node).contents().each(
        (_i, child) => {
            // parse text
            if (child.type === 'text') {
                res += $(child).text();
                return;
            }
            // parse element
            if (child.type !== 'tag') {
                return;
            }
            if (child.tagName === 'h4') {
                res += '\\end{enumerate}\n';
                res += '\\subsubsection{' + $(child).text() + '}';
                res += '\\begin{enumerate}\n';
            } else if (child.tagName === 'ol' || child.tagName === 'ul') {
                res += '\\begin{enumerate}\n';
                res += parseContents(child);
                res += '\\end{enumerate}\n';
            } else if (child.tagName === 'li') {
                res += '\\item ' + parseContents(child);
            } else if (child.tagName === 'strong') {
                res += '\\textbf{' + parseContents(child) + '}';
            } else if (child.tagName === 'em') {
                res += '\\textit{' + parseContents(child) + '}';
            } else if (child.tagName === 'p') {
                res += $(child).text() + '\n';
            }
        }
    );
    return res;
}

let filename = '';
let content = '';

const checkAndWriteFile = () => {
    if (!content) return;
    const path = `${__dirname}/${filename}.tex`;
    fs.writeFileSync(path, content);
    filename = '';
    content = '';
}

$('#equations-list').children().each(
    (_, el) => {
        if (el.tagName === 'ol') {
            content += '\\begin{enumerate}\n';
            content += parseContents(el);
            content += '\\end{enumerate}\n';
        } else if (el.tagName === 'h3') {
            checkAndWriteFile();
            if (el.tagName === 'h3') {
                filename = $(el).text();
            }
        }
    }
);

checkAndWriteFile();
