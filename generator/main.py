import os
import shutil

from article import Article

from config import OUTPUT_DIRECTORY, FAST

import templates

def clear_directory(directory):
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)

        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)

def copy_content(source_directory, destination_directory):
    for item_name in os.listdir(source_directory):
        shutil.copy(os.path.join(source_directory, item_name), os.path.join(destination_directory, item_name))

def write_file(filename, content):
    if filename.startswith("/"):
        filename = filename[1:]
    if not filename.endswith('.html'):
        filename = os.path.join(filename, "index.html")
    filename = os.path.join(OUTPUT_DIRECTORY, filename)
    file_directory = os.path.dirname(filename)
    if not os.path.isdir(file_directory):
        os.makedirs(file_directory)
    with open(filename, 'w') as file:
        file.write(content)


if not os.path.exists(OUTPUT_DIRECTORY):
    os.makedirs(OUTPUT_DIRECTORY)

if not FAST:
    clear_directory(OUTPUT_DIRECTORY)
copy_content('theme/static', OUTPUT_DIRECTORY)

article = Article('content/article/infinite-wfc')

output = templates.page.render(
    content=templates.article.render(
        content=article.get_html_content(),        
        title=article.get_title()
    )
)

write_file(article.url, output)