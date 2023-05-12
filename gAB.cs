public List<Book> getAllBooks() {
    List<Book> books = bookRepository.findAll();
    return books;
}
