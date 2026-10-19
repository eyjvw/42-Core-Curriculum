all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)📦 Creating library...$(RESET)"
	@$(AR) $(NAME) $(OBJECTS)
	@echo "$(CYAN)📚 $(NAME) created successfully.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing library...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJECTS) $(BONUS_OBJECTS)
	@echo "$(BLUE)📦 Creating library with bonus...$(RESET)"
	@$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)
	@touch $(BONUS_FLAG)
	@echo "$(CYAN)📚 $(NAME) created with bonus successfully.$(RESET)"

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all bonus clean fclean re
