import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="card_manufacturing",
    version="0.0.1",
    author="Maximilian Schommer",
    author_email="maxschommer@gmail.com",
    description="Tools for manufacturing POV business card",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/maxschommer/business_card",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    install_requires=[
        'plac',
        'Pillow',
        'opencv-python',
        'mecode',
        'drawSvg'
    ],
    extras_require={
    },
    python_requires='>=3.6',
)
