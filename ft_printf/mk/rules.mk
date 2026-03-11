all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@echo "$(BLUE)📦 Creating library...$(RESET)"
	@$(AR) $(NAME) $(OBJECTS)
	@echo "$(CYAN)📚 $(NAME) created successfully.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c includes/ft_printf.h
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing library...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
