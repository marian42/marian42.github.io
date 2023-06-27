import os
import shutil
import jinja2

from article import Article

OUTPUT_DIRECTORY = 'output'

def clear_directory(directory):
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)

        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)

def copy_content(source, destination):
    for item_name in os.listdir(source):
        shutil.copy(os.path.join(source, item_name), os.path.join(destination, item_name))

def write_file(filename, content):
    if filename.startswith("/"):
        filename = filename[1:]
    if not filename.endswith('.html'):
        filename = os.path.join(filename, "index.html")
    filename = os.path.join(OUTPUT_DIRECTORY, filename)
    os.makedirs(os.path.dirname(filename))
    with open(filename, 'w') as file:
        file.write(content)


if not os.path.exists(OUTPUT_DIRECTORY):
    os.makedirs(OUTPUT_DIRECTORY)

clear_directory(OUTPUT_DIRECTORY)
copy_content('theme/static', OUTPUT_DIRECTORY)

templates = jinja2.Environment(loader=jinja2.FileSystemLoader('theme/templates'))

page_template = templates.get_template('index.html')
article_template = templates.get_template('article.html')

article = Article('content/article/infinite-wfc')

output = page_template.render(
    content=article_template.render(
        content=article.get_html_content(),        
        title=article.get_title()
    )
)

write_file(article.url, output)