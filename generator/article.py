import os
import yaml
import re
from datetime import datetime

from mistune import create_markdown

from config import PLUGINS
from markdown_rendering import CustomHTMLRenderer

import templates
youtube_replacement = templates.youtube_embed.render(video="\\1")

def fix_markdown(markdown_text):
    # Replace hugo image commands with Markdown images
    pattern = r'{{<\s*img\s*"([^"]+)"\s*(?:"([^"]*)")?\s*>}}'
    replacement = r'![\2](\1)'
    markdown_text = re.sub(pattern, replacement, markdown_text)
    
    # HTML videos
    pattern = r'<video.*\s*src="\/article\/[^\/*]*\/([^"]*)"[^>]*>[^>]*>'
    replacement = r'![](\1)'
    markdown_text = re.sub(pattern, replacement, markdown_text)

    # HTML links
    pattern = r'<a\s*href="([^"]*)"\s*>([^<]*)<\/a>'
    replacement = r'[\2](\1)'
    markdown_text = re.sub(pattern, replacement, markdown_text)

    # Youtube command
    pattern = r'{{<\s*youtube\s([^\s>]*)\s*>}}'
    markdown_text = re.sub(pattern, youtube_replacement, markdown_text)    

    return markdown_text

class Article:
    def __init__(self, filename):
        if os.path.isdir(filename):
            filename = os.path.join(filename, "index.md")

        self.filename = filename
        self.directory = os.path.dirname(filename).replace('\\', '/')
        self.slug = self.directory.split('/')[-1]
        self.url = '/article/' + self.slug + "/"

        with open(filename, 'r', encoding="utf8") as file:
            file_content = file.read()
            
        dashes_index = file_content.find('---')
        file_content = file_content[dashes_index + 4:]
        
        dashes_index = file_content.find('---')
        config = file_content[:dashes_index]
        self.config = yaml.safe_load(config)

        self.date = self.config['date']

        if type(self.date) == datetime:
            self.date = self.date.date()

        self.title = self.config['title']

        file_content = file_content[dashes_index + 4:]
        fold_index = file_content.find('<!--more-->')

        if fold_index == -1:
            fold_index = len(file_content)

        self.markdown_summary = file_content[:fold_index]

        self.renderer = CustomHTMLRenderer(self)
        
        self.markdown_content = self.markdown_summary + file_content[fold_index + 11:]

        self.markdown_content = fix_markdown(self.markdown_content)
        self.markdown_summary = fix_markdown(self.markdown_summary)

    def get_html_content(self):
        self.renderer.use_relative_image_urls = True
        render = create_markdown(renderer=self.renderer, plugins=PLUGINS)
        return render(self.markdown_content)
    
    def get_html_summary(self):
        self.renderer.use_relative_image_urls = False
        render = create_markdown(renderer=self.renderer, plugins=PLUGINS)
        return render(self.markdown_summary)