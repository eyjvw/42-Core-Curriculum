all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

bonus: $(NAME_BONUS)
	@echo "$(GREEN)✅ Bonus compilation completed: $(NAME_BONUS)$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJ_DIR) $(BONUS_OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJECTS) -o $(NAME_BONUS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $(PHILO_INC) $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $(BONUS_INC) $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binaries...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus