from PIL import Image

for i in [1, 2, 3]:
    # Load the original image
    image = Image.open(f"logo{i}.png")  # Replace with your file name

    # Step 1: Resize the image to 272x272 while keeping aspect ratio
    resized_image = image.resize((272, 272), Image.LANCZOS)

    # Step 2: Create a new 480x272 image with a black background
    final_image = Image.new("RGB", (480, 272), (0, 0, 0))  # (0,0,0) is black

    # Step 3: Paste the resized image at the center
    x_offset = (480 - 272) // 2  # Centered horizontally
    final_image.paste(resized_image, (x_offset, 0))

    # Step 4: Save the result
    final_image.save(f"logo{i}-brain.png")  # Change to PNG if needed

    # Show the final result (optional)
    final_image.show(f"logo{i}-brain.png")
