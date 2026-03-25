FROM oven/bun:1.1

WORKDIR /app

COPY backend/game/config/package.json ./
RUN bun install

COPY backend/game/src ./src
COPY backend/db /db

RUN mkdir -p /app/data

EXPOSE 4002

CMD ["bun", "run", "src/index.ts"]
