
from mistune import HTMLRenderer
import shutil
import os
from PIL import Image

from config import OUTPUT_DIRECTORY, IMAGE_WIDTH, FAST
import templates

small_images = set()

class MarkdownImage:
    def __init__(self, article, base_url):
        self.base_url = base_url
        self.article = article
        self.source_file_path = os.path.join(self.article.directory, base_url)

        self.is_remote = False

        if not os.path.isfile(self.source_file_path):
            self.is_remote = True
            return

        full_size_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], base_url)
        target_directory = os.path.dirname(full_size_path)
        if not os.path.isdir(target_directory):
            os.makedirs(target_directory)

        if not FAST or not os.path.isfile(self.source_file_path):
            shutil.copy(self.source_file_path, target_directory)
            
        filename, file_extension = os.path.splitext(base_url)
        self.small_image_name = filename + "_" + str(IMAGE_WIDTH) + file_extension
        small_image_path = os.path.join(OUTPUT_DIRECTORY, self.article.url[1:], self.small_image_name)

        self.is_small = False
        if FAST and os.path.isfile(small_image_path):
            return

        image = Image.open(self.source_file_path)
        width, height = image.size

        if width <= IMAGE_WIDTH:
            self.is_small = True
        else:
            new_height = int(height * IMAGE_WIDTH / width)
            resized_image = image.resize((IMAGE_WIDTH, new_height))
            resized_image.save(small_image_path)

    def get_source(self, relative):
        if self.is_remote:
            return self.base_url
        
        filename = self.base_url if self.is_small else self.small_image_name

        if relative:
            return filename
        else:
            return self.article.url + filename        
    
    def get_link(self, relative):
        if self.is_remote:
            return self.base_url
        
        if relative:
            return self.base_url
        else:
            return self.article.url + self.base_url
        
image_cache = dict()

class CustomHTMLRenderer(HTMLRenderer):
    def __init__(self, article, use_relative_image_urls=True):
        super().__init__()
        self.article = article
        self.use_relative_image_urls = use_relative_image_urls
        
    def image(self, alt, url, title=None):
        global image_cache

        key = (self.article.slug, url)
        if key in image_cache:
            image = image_cache[key]
        else:
            image = MarkdownImage(self.article, url)
            image_cache[key] = image
        
        return templates.image.render(url=image.get_link(self.use_relative_image_urls), src=image.get_source(self.use_relative_image_urls), alt=alt)