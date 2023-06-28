import os
import yaml
import re
from datetime import datetime

from mistune import create_markdown

from markdown_rendering import CustomHTMLRenderer

def fix_images(markdown_text):
    pattern = r'{{< img "([^"]+)" "([^"]*)" >}}'
    replacement = r'![\2](\1)'
    return re.sub(pattern, replacement, markdown_text)

class Article:
    def __init__(self, filename):
        if os.path.isdir(filename):
            filename = os.path.join(filename, "index.md")

        self.filename = filename
        self.directory = os.path.dirname(filename)
        self.slug = self.directory.split('/')[-1]
        self.url = '/article/' + self.slug + "/"

        with open(filename, 'r') as file:
            file_content = file.read()
            
        dashes_index = file_content.find('---')
        file_content = file_content[dashes_index + 4:]
        
        dashes_index = file_content.find('---')
        config = file_content[:dashes_index]
        self.config = yaml.safe_load(config)

        self.date = self.config['date']

        file_content = file_content[dashes_index + 4:]
        fold_index = file_content.find('<!--more-->')
        self.markdown_summary = file_content[:fold_index]

        self.renderer = CustomHTMLRenderer(self)
        
        self.markdown_content = self.markdown_summary + file_content[fold_index + 11:]

        self.markdown_content = fix_images(self.markdown_content)
        self.markdown_summary = fix_images(self.markdown_summary)

    def get_html_content(self):
        render = create_markdown(renderer=self.renderer)
        return render(self.markdown_content)
    
    def get_html_summary(self):
        render = create_markdown(renderer=self.renderer)
        return render(self.markdown_summary)
    
    def get_title(self):
        return self.config["title"]